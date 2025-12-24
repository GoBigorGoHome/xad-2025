const { execSync } = require('child_process');
const fs = require('fs');
const path = require('path');

const distDir = path.join(__dirname, 'dist');
const projectsDir = __dirname;

if (fs.existsSync(distDir)) fs.rmSync(distDir, { recursive: true });
fs.mkdirSync(distDir);

// Helper: Get last commit date for the slides.md file
function getLastUpdated(folder, fileName) {
  try {
    // Gets the ISO date of the last commit for this specific file
    const dateStr = execSync(`git log -1 --format=%cd --date=format:'%Y-%m-%d' -- "${path.join(folder, fileName)}"`, { encoding: 'utf-8' });
    return dateStr.trim() || new Date().toISOString().split('T')[0]; // Fallback to today
  } catch (e) {
    return new Date().toISOString().split('T')[0];
  }
}

// 1. Get folders with slides.md
const folders = fs.readdirSync(projectsDir).filter(file => {
  const fullPath = path.join(projectsDir, file);
  return fs.statSync(fullPath).isDirectory() && 
         fs.existsSync(path.join(fullPath, 'slides.md')) &&
         !['node_modules', 'dist', '.git'].includes(file);
});

const manifest = [];

function copyImagesRecursive(src, dest, filter) {
  if (!fs.existsSync(src)) return;
  
  const files = fs.readdirSync(src);

  files.forEach(file => {
    const srcPath = path.join(src, file);
    const destPath = path.join(dest, file);

    const stat = fs.statSync(srcPath);

    if (stat.isDirectory()) {
      // 1. Skip node_modules, dist, and ANY folder starting with a dot
      if (file !== 'node_modules' && file !== 'dist' && !file.startsWith('.')) {
        copyImagesRecursive(srcPath, destPath, filter);
      }
    } else if (stat.isFile() && filter.test(file)) {
      // 2. Only copy if it's an image file
      if (!fs.existsSync(dest)) fs.mkdirSync(dest, { recursive: true });
      fs.copyFileSync(srcPath, destPath);
    }
  });
}

folders.forEach(folder => {
  const projectPath = path.join(projectsDir, folder);
  const slidesPath = path.join(projectPath, 'slides.md');
  const distSubDir = path.join(distDir, folder);

  const content = fs.readFileSync(slidesPath, 'utf-8');
  
  // 1. Determine the Engine
  const isMarp = content.includes('marp: true');
  
  // 2. Extract Title
  const titleMatch = content.match(/^title:\s*["']?(.*?)["']?$/m);
  const displayTitle = titleMatch ? titleMatch[1] : folder.replace(/-/g, ' ');
  const updatedDate = getLastUpdated(projectPath, 'slides.md');

  console.log(`\n🚀 Building ${isMarp ? '[Marp]' : '[Slidev]'}: ${displayTitle}`);
  fs.mkdirSync(distSubDir, { recursive: true });

  if (isMarp) {
    // 3. Marp Build Command
    // --html allows raw HTML in slides, --base sets asset paths
    // 3.1. Build Marp HTML
    execSync(`npx marp slides.md --theme lecture.css --html --output ../dist/${folder}/index.html`, { 
      cwd: projectPath, 
      stdio: 'inherit' 
    });

    // 3.2. Copy ONLY images to dist
    const imageExtensions = /\.(png|jpe?g|gif|svg|webp|avif)$/i;

    fs.readdirSync(projectPath).forEach(file => {
      const srcPath = path.join(projectPath, file);
      const destPath = path.join(distSubDir, file);

      // Check if it's a file and matches our image extensions
      if (fs.statSync(srcPath).isFile() && imageExtensions.test(file)) {
        fs.copyFileSync(srcPath, destPath);
        console.log(`  📸 Copied image: ${file}`);
      } 
      // If you have images in subfolders, we handle them recursively
      else if (fs.statSync(srcPath).isDirectory() && file !== 'node_modules' && !file.startsWith('.')) {
        copyImagesRecursive(srcPath, destPath, imageExtensions);
      }
    });
  } else {
    // 4. Slidev Build Command
    execSync(`pnpm exec slidev build slides.md --base /${folder}/ --out ../dist/${folder}`, { 
      cwd: projectPath, 
      stdio: 'inherit' 
    });
  }

  manifest.push({ title: displayTitle, date: updatedDate, path: `/${encodeURIComponent(m.folder)}/` });
});

const listItems = manifest
  .map(m => `
    <li>
      <a href="${m.path}">
        <span class="title">${m.title}</span>
        <span class="date">Last updated: ${m.date}</span>
      </a>
    </li>`)
  .join('\n');

const htmlContent = `
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Slide Deck Collection</title>
  <style>
    body { font-family: -apple-system, system-ui, sans-serif; padding: 4rem 1rem; background: #f3f4f6; color: #1f2937; max-width: 700px; margin: 0 auto; }
    h1 { font-size: 2.25rem; margin-bottom: 2rem; text-align: center; }
    ul { list-style: none; padding: 0; }
    li { margin-bottom: 1.25rem; }
    a { display: flex; justify-content: space-between; align-items: center; padding: 1.5rem; background: white; border-radius: 12px; text-decoration: none; color: inherit; transition: transform 0.2s, box-shadow 0.2s; box-shadow: 0 1px 2px rgba(0,0,0,0.05); }
    a:hover { transform: translateY(-3px); box-shadow: 0 10px 15px -3px rgba(0,0,0,0.1); }
    .title { font-weight: 700; font-size: 1.2rem; color: #2563eb; }
    .date { font-size: 0.875rem; color: #6b7280; font-variant-numeric: tabular-nums; }
    @media (max-width: 500px) { a { flex-direction: column; align-items: flex-start; gap: 0.5rem; } }
  </style>
</head>
<body>
  <h1>信奥队课件集</h1>
  <ul>${listItems}</ul>
</body>
</html>`;

fs.writeFileSync(path.join(distDir, 'index.html'), htmlContent);

console.log('\n✅ Build complete.');