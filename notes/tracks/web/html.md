HTML is a text-based representation of the structure of the page. Using nested tags you can define the hierarchy of the elements.

With HTML we only create a structure of the page, not the visual representation of it.

HTML is made up of lots of nested tags that map to a tree structure, with opening tags and closing tags that determine the structure of the page.

`<head>` section contains the __metadata__ of the page.

`<body>` tag contains the visible content displayed by the browser.

You can run a static server in CS50 IDE, by running `http-server` command. It's a live server that will auto-reload the page on save.

`img` is an example of self-closing tag.

To create a link we can use `<a href="http://site.com">Visit Site</a>` tag, with `href` standing for Hyperlink Reference.

You can create separate paragraphs using `<p>` tag.

For headings we can use `<h1> - <h6>` tags.

To create tables we can create a table, table row and table cell data structure:

```
<table>
    <tr>
        <td>cell 1</td>
        <td>cell 2</td>
    </tr>
    <tr>
        <td>cell 3</td>
        <td>cell 4</td>
    </tr>
</table>
```

We can create forms with inputs as well:

```
<form action="https://www.google.com/search" method="get">
    <input type="text" name="q" />
    <input type="submit" value="Submit Form" />
</form>
```