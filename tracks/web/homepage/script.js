let catFactEl = document.querySelector('.js-cat-fact');
let catImgEl = document.querySelector('.js-cat-img');
let catNameEl = document.querySelector('.js-cat-name');
let copyEl = document.querySelector('.js-copy');
let formEl = document.querySelector('.js-contact-form');
let formResultEl = document.querySelector('.js-form-result');
let emailEl = document.querySelector('.js-form-result__email');
let messageEl = document.querySelector('.js-form-result__message');

copyEl.innerHTML = (new Date()).getFullYear();

const get = url => {
  return fetch(url)
    .then(res => res.json())
    .then(res => res);
}

if (formEl) {
  formEl.addEventListener('submit', e => {
    e.preventDefault();

    let email = e.target.email.value;
    let message = e.target.message.value;

    formResultEl.classList.add('is-visible');
    emailEl.querySelector('.value').innerHTML = email;
    messageEl.querySelector('.value').innerHTML = message;
  });
}

if (catFactEl && catImgEl && catNameEl) {
  get('https://api.thecatapi.com/v1/images/search')
    .then(res => catImgEl.src = res[0].url);

  get('https://randomuser.me/api/')
    .then(res => {
      let name = `${res.results[0].name.title} ${res.results[0].name.first} ${res.results[0].name.last}`;
      catNameEl.innerHTML = name;
    })

  get('https://catfact.ninja/fact')
    .then(res => catFactEl.innerHTML = res.fact);
}
