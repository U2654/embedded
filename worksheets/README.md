# Worksheets

The following worksheets are written in Markdown and are prepared to be build with pandoc. If you have no pandoc installation follow the guide

## Installation

1.  Install pandoc from <http://pandoc.org/>. You also need to install [LaTeX](https://en.wikibooks.org/wiki/LaTeX/Installation#Distributions).
2.  Clone this repository
3.  Move the template `embedded.latex` to your pandoc templates folder. The location of the templates folder depends on your operating system:
      - Unix, Linux, macOS: `/Users/USERNAME/.local/share/pandoc/templates/` or `/Users/USERNAME/.pandoc/templates/`
      - Windows Vista or later: `C:\Users\USERNAME\AppData\Roaming\pandoc\templates\`

If there are no folders called `templates` or `pandoc` you need to create them and put the template `embedded.latex` inside. 
You can find the default user data directory on your system by looking at the output of `pandoc --version`.

 

## Usage

1.  Open the terminal and navigate to the repository.

2.  Execute the following command

    ``` bash
    pandoc lesson1.md --from markdown --template embedded -o lesson1.pdf
    ```

   
