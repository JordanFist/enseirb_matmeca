import Vue from 'vue'
import Router from 'vue-router'
import Home from '../components/Home.vue'
import Login from '../components/Login.vue'
import Room from '../components/Room.vue'

Vue.use(Router)

export default new Router({
    routes: [
       {path: '/', component: Home},
       {path: '/room', component: Room},
       {path: '/login', component: Login}
    ]
})