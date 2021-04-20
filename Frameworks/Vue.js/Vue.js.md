# Vue.js

## Intro & Setup

- Vue.js is a JS / TypeScript front-end framework
- Used to create dynamic and data-driven websites (single page applications - SPA)
- Vue.js injects (dynamic) data into a HTML template (into the DOM tree) and updates the view automatically

**Tip:** Use Visual Studio Code with following plugins: Live Server and Veture

## Vue Basics

### Vue App, Click Events and Vue Directives

How to use Vue.js:

```
// main.html
<html>
    <head>
        <script src="https://unpkg.com/vue@3.0.2"></script>
    </head>
    <body>
        <div id="app">
            <p>{{ title }} </p>
            <button v-on:click="year++">Increase year</button>
        </div>
        <script src="app.js"></script>
    </body>
</html>
```

```
// app.js
const app = Vue.createApp({
    data() {
        return {
            title: "My Title",
            year: 2000
        }
    }
})
app.mount("#app')
```

### Mouse Events, Outputting lists, Attributes Binding and Dynamic Classes

- <div @mouseover="handleEvent($event, 1)"></div>
- <ul> <li v-for="book in books"> <h1>{{ book }}</h1> </li></ul>
- <a v-bind:href="url"></div>
- <div v-if="showBooks"></div>

## Vue in Bigger Projects as SPA Using the Vue CLI

### Start and Vue files

- `npm install -g @vue/cli`
- `vue create modal-project`
  * A .vue file contains three tags: template, script and style
  * `main.js` loads the .vue file

### Template Refs to DOM Elements

- In Vue.js DOM elements are selected by template refs instead of `element.querySelector()`.
  * `<input type="text" ref="myinput"></input>`
  * `methods: { handleClick() { console.log(this.$refs.myinput) } }`

### Multiple Components

- Usually, a Vue/HTML site consists of multiple elements (components)
- Therefore, split up the site into multiple well-encapsulated components (header, navbar, articles etc.) and combine it in the root component (`App.vue`).
- Components that should be used, must be registered in the Vue app inside the `components` object.

### Scoped CSS Styles

- `<style scoped>...</style>` or
- use specific CSS classes for your HTML elements, e.g. `<p class="container">` or
- use main.js: `import "./assets/global.css"

### Props

- Pass data from parent to child module:
  ```
  <script>
    export default {
      props: [ "myprop" ] // Register it inside the component
    }
  </script>
  
  // Use it in another module:
  <MyComponent myprob="Test"></MyComponent>
  ```

### Emitting Custom Events

- A custom event can be fired from a child component and listened to it in a parent component.

```
// Child component
methods: {
    closeModal() {
        this.$emit("nameOfEvent")
    }
}

// Parent component
<Modal ... @nameOfEvent="myHandler" />
```

- Use event modifiers to customize event handling

```
<button @click.right="toggleButton">Open modal</button>
```

### Slots

- More complex information, e.g. a HTML form, can be injected by using slots.

```
// App.js
<Modal><p>My slot info</p></Modal>

// Modal
<h1>...</h1>
<slot></slot>
```

- Name slots

```
// App.js
<Modal><template v-slot:slotName>My slot info</template></Modal>

// Modal
<h1>...</h1>
<slot name="slotName"></slot>
```

### Teleport

- A teleporter injects a HTML element somewhere in the DOM tree.

```
// index.html
<div id="app"></div>
<div class="teleporterTarget></div>

// App.vue
<teleport to=".modals">
</teleport>
```

## Fetching Data

- Goal: Fetch data from inside a view.

```
<script>
export default {
    data() {...},
    mounted() { fetch("http://localhost:3000/jobs").then(res => res.json()).then(data => this.jobs = data } // Async and returns a JS Promise
}
</script>
```

**Tip:** Use `json-server` NPM package to mock a database as db.json and to provide an API automagically.
```
{
  "blogs": [ { "title": "test", "id": 1 } ] // Can be accessed by localhost:3000/blogs/id
}
```

## The Vue Router

### Router Basics

- Goal: Create a SPA with different endpoints:
  * mysite.com/index -> App.vue (without sending a new HTTP request to a server)
  * mysite.com/about -> About.vue
- This requires to install the Vue router package: `vue create my-project` (enable `Router` which creates `Router/index.js`).

### Router Links

Vue intercepts the HTTP request and just replaces the current view component: `<router-link to="/">Home</router-link><router-view/>`

or with parameters: `<router-link :to="{ name: 'JobDetails', params: {id: job.id }}">Home</router-link><router-view/>`

### Folder Structure

Vue app:

- node_modules
- public
- src
  * assets
  * components -> reusable HTML components which are used in different views
  * router
  * views
- App.vue
- main.js

### Route parameters

- router/index.js: `{ path: "jobs/:id", name: "JobDetails", component: JobDetails }`

```
// JobDetails.vue
<template>
    <h1>Job id: {{ $route.params.id }}</h1>
</template>
```

### Route Redirects and 404

```
// router/index.js
const routes = [
    // redirects
    {
        path: "/old-path",
        redirect: "/new-path"
    }
    // 404 errors
    {
        path: "/:catchAll(.*)",// The parantheses shall contain a regex!
        name: "NotFound",
        component: NotFound
    }
]
```

## To Composition API

Old way (the Options API):

```
// Component object
export default {
    data() {
        return { books: [], showButton: false }
    }
    methods() {
        ...
    }
    mounted() {
        ...
    }
}
```

A new way (the Composition API)

```
// Component object
export default {
    // The goal is to better group things together
    setup() { // Watch out: "this" is not available to refer to this component
        // data
        // methods
        // computed
        // lifecycle hooks
    }
}
```

Variables must be made reactive by using (template) refs:

```
import { ref } from "vue"

export default {
    setup() {
        const name = ref("test")
        
        const handleClick = () => {
            name.value = "changed" // .value unwraps the ref
        }
    }
}
```

- An alternative: `import { reactive } from "vue` -> But, this does not work for primitive values!
- `computed()` can be used inside the `setup()` function to return a value based on an existing value.
- The composition API offers the `watch()` and `watchEffect()` hook.
