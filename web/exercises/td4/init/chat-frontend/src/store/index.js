import Vue from "vue";
import Vuex from "vuex";

Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    loggedin: false,
    username: ""
  },
  mutations: {
    login(state, name) {
      state.loggedin = true,
        state.username = name
    },
    logout(state) {
      state.loggedin = false
    }
  },
  actions: {
    login: function (context, username) {
      context.commit("login", username);
    },
    logout: function (context) {
      context.commit("logout");
    }
  },
  getters: {
    username: function (state) {
      return state.username;
    },
    loggedIn: function (state) {
      return state.loggedin;
    }
  }
});
