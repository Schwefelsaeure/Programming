#/bin/bash

# Convert all image files in folder to PDF and apply optical character recognition (OCR) using tesseract.

ext="jpeg"

for file in $(find . -type f -name "*.${ext}")
do
    tesseract "${file}" "${file%.${ext}}" -l deu pdf
done
