# LibreOffice

## Useful Extensions

- Code Highlighter
- VRT Network Equipment

## LO Draw

To get a cropped PDF either use following steps and tools:

1. Mark all objects in drawing area (Ctrl + A).
2. Export as SVG (activate checkbox "Extract selection").
3. `rsvg-convert -f pdf in.svg > out.pdf` (Note: rsvg-convert preservers the alpha levels correctly).

Or following steps and tools:

1. Export as PDF (Note: batch command `soffice --convert-to pdf in.odg` extracts **all** pages).
2. pdfcrop --hires in.pdf out.pdf

Note: You can use `qpdf --split-pages out.pdf out.qpdf.pdf` to write each PDF page into an own file.
