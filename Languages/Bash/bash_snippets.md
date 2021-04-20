# Bash Snippets

## ImageMagick

Convert multiple JPG files to PDF:

```
mogrify -format pdf *.jpg
```

Watch out: `/etc/ImageMagick-x/policy.xml` must contain `<policy domain="coder" rights="all" pattern="PDF" />`.

## librsvg

Convert SVG file PDF:

```
rsvg-convert -f pdf in.svg > out.pdf
```

## Qpdf

Extract pages from PDF file:

```
# Page notations like "1", "1,2" or "1,2,4-5".
qpdf --pages in.pdf 1,2,4-5 -- in.pdf out.pdf
```

Merge multiple PDF files into one:

```
qpdf --empty --pages *.pdf -- out.pdf
```

Rotate pages:

```
qpdf in.pdf out.pdf --rotate=+90:2,4,6 --rotate=180:7-9
```

## Search and Replace in Files (find and sed)

Check for occurences using find and grep (searching for pattern "fill={...}"):

```
find . -type f -name "*.tex" -exec grep -EHn "fill=(\{.+\})" {} \;
```

Replace occurences (by "fill=AgentColor"):

```
find . -type f -name "*.tex" -exec sed -i -r -e 's/fill=(\{.+\})/fill=AgentColor/g' {} \;
```

## Vadere

Calculate md5sum for trajectory files under "basic" subdirectory:

```
find .  -type f -regex ".*basic.*\.trajectories" -exec md5sum {} \;
```

Run vadere-console multiple time with a scenario file:

```
for i in {1..500}; do java -jar vadere-console.jar scenario-run --scenario-file ../../VadereModelTests/TestGNM/scenarios/basic_1_chicken_gnm1.scenario; done
```

Reset all scenario files:

```
git status | grep -E "\.scenario$" | cut --delimiter=" " --fields 3 | xargs git checkout --
```

## Find Length of Filenames and File Paths

- Find filenames greater or equal 255: `find . -type f -regextype egrep -regex '.{255,}'`
- Print five longest filenames: `find . -type f | awk '{ print length, $0 }' | sort -nr | head -n 5`
