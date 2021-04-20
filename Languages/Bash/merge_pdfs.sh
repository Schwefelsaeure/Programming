#/bin/bash

# Merge all pdfs into one pdf using qpdf.

qpdf --empty --pages *.pdf -- $(date '+%Y-%m-%dT%H-%M-%S').pdf
