import Vue from 'vue';

import App from './components/App.vue';

import BootstrapVue from 'bootstrap-vue';
import 'bootstrap/dist/css/bootstrap.min.css';
import 'bootstrap-vue/dist/bootstrap-vue.css';

import VueMoment from 'vue-moment';

Vue.use(BootstrapVue);
Vue.use(VueMoment);

new Vue({
  el: '#app',
  render: h => h(App)
})

