#let setup(year, kind, body) = {
  set document(title: str(year) + "年数据结构与算法A期中" + kind, author: "扫描资料整理")
  set text(font: ("Songti SC", "Times New Roman"), size: 10.5pt, lang: "zh")
  set par(justify: true, leading: 0.65em, spacing: 0.8em)
  set page(paper: "a4", margin: (x: 20mm, top: 20mm, bottom: 19mm),
    header: text(size: 8pt, fill: luma(100))[数据结构与算法 A · #year 年期中 #kind #h(1fr) 扫描资料重排],
    footer: align(center, text(size: 8pt)[#context counter(page).display("1")]))
  show heading: set text(font: "Heiti SC")
  show heading.where(level: 1): set block(above: 1.3em, below: 0.8em)
  show raw: set text(font: ("Menlo", "Songti SC"), size: 8.5pt)
  show raw.where(block: true): it => block(fill: luma(247), inset: 9pt, width: 100%, breakable: true, it)
  align(center)[#text(font: "Heiti SC", size: 20pt)[数据结构与算法 A] #v(5pt) #text(size: 14pt)[#year 年期中 · #kind]]
  v(10pt)
  body
}
#let note(body) = block(width: 100%, fill: luma(245), inset: 9pt, text(size: 9pt, body))
#let q(n, body) = {block(above: 10pt, below: 5pt)[#strong(n + "．")#body]}
#let fig(path, width: 80%) = align(center, image("assets/" + path, width: width))
#let space(h: 14mm) = v(h)
