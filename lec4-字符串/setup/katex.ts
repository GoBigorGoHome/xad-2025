import { defineKatexSetup } from '@slidev/types'

export default defineKatexSetup(() => {
  return {
    macros: {
        '\\border': '\\mathrm{border}',
        '\\pref': '\\mathrm{pref}',
        '\\lcp': '\\mathrm{lcp}',
    },
  }
})
