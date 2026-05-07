import { defineKatexSetup } from '@slidev/types'

export default defineKatexSetup(() => {
  return {
    macros: {
        '\\border': '\\mathrm{border}',
        '\\pref': '\\mathrm{pref}',
        '\\lcp': '\\mathrm{lcp}',
        '\\rev' : '\\overleftarrow{#1}',
        '\\rad' : '\\operatorname{rad}',
        '\\lcm' : '\\operatorname{lcm}',
        '\\multichoose' : '\\left(\\kern-.3em\\left( \\genfrac{}{}{0pt}{}{#1}{#2} \\right)\\kern-.3em\\right)',
    },
  }
})
