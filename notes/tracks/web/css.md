We can add styles to the elements directly using `style` attribute, ie:

```
<h1 style="color: blue;">Hello world!</h1>
```

where

- `color` is property
- `blue` is a value

CSS can get repetitive by adding same properties to different element.

We can also have the CSS properties inherited by the children, by moving the style to the shared parent.

Some other useful properties:

- `text-align` - text alignment
- `font-size` - text size
- `background-color` - background color of the element

If you add a `style` attribute to an element, it will only apply to that specific element, which can be sub-optimal if you want to re-use the styling.

This style of CSS declaration is called inline, instead we can write our styles in the head section, ie:

```
<head>
    <style>
        h2 {
            text-align: center;
            color: blue;
        }
    </style>
</head>
```

This way we can let HTML define the structure of the page and CSS the styling of the page, which is a better design.

We can further improve our code by using a `class` attribute in our HTML elements, which allows us to reuse the styling for multiple elements.

HTML elements can also have multiple classes, ie:

```
<h1 class="title green">Hello world!</title>
```

We can also separate our CSS into a separate file and load it into HTML file with:


```
<head>
    <link rel="stylesheet" href="styles.css" />
</head>
```

where `rel` is a relationship of stylesheet, meaning the file you are linking is the stylesheet.

It is advantageous because you might have different HTML pages using the same CSS file, write it once and use it everywhere. You can also have multiple different CSS files that apply to specific pages only.

HTML technically doesn't care about the indentation, but it helps with organization due to HTML's hierarchical nature.