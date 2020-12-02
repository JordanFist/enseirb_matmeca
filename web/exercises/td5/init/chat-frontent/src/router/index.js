import Vue from 'vue'
import Router from 'vue-router'

import Home from './../components/Home'
import Room from './../components/Room'
import Login from './../components/Login'
import Profile from './../components/Profile'

Vue.use(Router)

export default new Router({
    routes: [
        { path: '/', name: 'Home', component: Home },
        { path: '/room', name: 'Room', component: Room },
        { path: '/login', name: 'Login', component: Login },
        { path: '/profile', name: 'Profile', component: Profile }
    ]
})
