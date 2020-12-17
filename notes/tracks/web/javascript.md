HTML page is modeled as a tree structure. All nested elements are represented as nodes of that tree, where each nested element is a child of a node in the tree. This model is referred to as Document Object Model.

JS allows us to manipulate DOM, extract, update and replace parts of our page without refreshing.

One of the ways to output the information in a browser is by using an `alert` function.

If you want to reference an HTML element in JS, you need to give it a particular name, via `id`, `class` or `name` attribute.

We can then use `document.querySelector` function to select the element.

But this selects an element itself so for elements such as form inputs, what we are likely more interested in is getting it's `.value` attribute.

We can add a form and have form call a function when it is submitted, but because forms have default behaviour of sending the data to it's action attribute, we need to stop it with `<form onsubmit="handleSubmit(); return false;">`

Just like we can read the information from the DOM, we can update DOM as well using JS.

We can do that by using `innerHTML` property of HTML element and setting it's value, ie:

```
document.querySelector('#result').innerHTML = document.querySelector('#name').value;
```

We can access the functions and values we define in our HTML file in a Browser JS console, which is a useful debugging tools.

We can also change the style of the page using JS, not just the HTML content.

There is a concept of *anonymous function* in JS, which is often used in places where you need to provide a function, but don't necessarily want to create a named function, for example for event handlers, such as `.onclick`.

If you are accessing DOM elements with JS you have to be careful to not try to select the elements before they are defined down the page. A simple fix for that would be to move `<script>` tag to the bottom of the page, before the closing `</body>` tag.

There are multiple other events that we can listen for and handle using event handler functions. The event listeners need to be attached to a specific HTML element.

We can access the element that triggered the event handler by using `this` keyword. We can think of `this` as a special variable that contains some kind of context for how a function is called.

If you want to run a function every number of milliseconds you can use `setInterval` function, that takes a function to run and time in milliseconds of how often you want to run it.

To get geolocation of your current position we can use this:

```
navigator.geolocation.getCurrentPosition(function(position) {
  document.write(position.coordinates.latitude + ', ' + position.coordinates.longitude);
})
```

which uses what is known as *callback function*, which in this case will have a `position` parameter that can give us information.