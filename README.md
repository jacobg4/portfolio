# Jacob Givhan — Portfolio

Personal software portfolio: a static site (HTML/CSS/JS, no build step) showcasing
[Blood & Burden](https://bloodburden.labcabin.org) and coursework projects.

## Structure

- `index.html` — page content
- `style.css` — styling
- `script.js` — nav toggle + source-code viewer modal
- `assets/img/` — images
- `projects/` — full source for each project; these are the files shown in the "View Source" modal on the project cards

## Running locally

No build step required — serve the directory with any static file server, e.g.:

```bash
python -m http.server 5500
```

Then open `http://localhost:5500`.
