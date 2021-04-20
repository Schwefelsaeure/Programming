# Create a Website

Creating a website is a two-step process:

1. Design the site using an UI design tool (e.g., Adobe Experience, Akira or Inkscape).
2. Code the design in HTML, CSS and Javascript.

## Design the Site

1. Choose background color or image.
2. Place a container on top of the background. **Watch out:** Contrast to background matters!
3. Place navigation bar on the top or at the side of the container.
4. Place the logo near the navigation bar. **Watch out:** Apply visual hierarchy guidelines! I.e., each element should easily be recognized (by using physical location, separators, size, color, font size etc.).
5. Place headlines.
6. Place content.
7. Rearrange site for mobile screens (i.e., add line breaks after content elements: logo LINEBREAK navbar LINEBREAK first header and content LINEBREAK etc.).

**Goal:** Make it easier for the reader! Guide the reader through the content!

## Code the Site in HTML/CSS/JS

TODO: https://www.youtube.com/watch?v=HKuDR0fYtCY

1. Create directory for new website with subdirs `html`, `css`, `js` and `images` use a text editor to write HTML, CSS and JS.
2. Create all design elements using the correct HTML tags (e.g., wrap navigation in `<nav>` tag and headlines in `<h1>` tags). **Watch out:** Assign classes and ids for all important elements.
3. Place all HTML elements using CSS. **Watch out:** Use classes and ids from previous step.
4. Write JS to make interaction possible (e.g., toggle a navigation bar by clicking a button).

**Tips:**

- Use an editor with auto-code-generation and boiler-plate-code-generation (HTML head etc.). E.g. Visual Studio Code.
- For HTML and CSS, think of every content element as block which can be freely arranged on the screen (side by side, sequentially or on top of each other).
- Copy & paste colors and other element information from design tool to HTML text editor.
- Place code editor and browser side by side and watch result immediately when saving editor content.
- Use browser to show default CSS style for each element.
- Either write whole HTML code first and then CSS code or write it in parallel.
- Mobile first!
  * Arrange content for small screens first.
  * Then, use CSS media queries to lay out content for bigger screens.

## Tips

Document design decisions as `Design Guide.md` and obey design principles. Start with the logo and derive following information for the whole website:

- Typography: Use one or two fonts (one serif, one sans-serif font)
- Colors: Repeat same color tones for header and footer and a different tone for the main content.
- Layout and composition: See "Website Layout - XY (Draft).svg"
- Images: No images yet

## Resources

### Articles

- https://uxplanet.org/open-design-freeware-tools-for-designers-f7bdde99f2e0

### HTML/CSS/JS Tools

- https://www.colorzilla.com/gradient-editor/
- https://fonts.google.com/
