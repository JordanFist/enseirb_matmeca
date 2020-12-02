import Vue from 'vue'
import router from './router'
import store from './store'

import App from './components/App.vue'

import BootstrapVue from 'bootstrap-vue'
import 'bootstrap/dist/css/bootstrap.min.css'
import 'bootstrap-vue/dist/bootstrap-vue.css'

import VueMoment from 'vue-moment';

Vue.use(BootstrapVue);
Vue.use(VueMoment);

new Vue({
  el: '#app',
  router,
  store,
  render: h => h(App)
})

