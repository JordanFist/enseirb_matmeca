import Vue from "vue";
import Vuex from "vuex";

Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    loggedin: false,
    username: "",
    themeColor: "info"
  },
  mutations: {
    COLOR(state, color) {
      state.themeColor = color;
    },
    LOGIN(state, username) {
      state.loggedin = true;
      state.username = username;
    },
    LOGOUT(state) {
      state.loggedin = false;
      state.username = "";
      state.themeColor = "info";
    }
  },
  actions: {
    color(commit, color) {
      this.commit("COLOR", color);
    },
    login(commit, username) {
      this.commit("LOGIN", username);
      localStorage.setItem("username", username);
    },
    logout() {
      this.commit("LOGOUT");
      localStorage.removeItem("username");
    },
    init(){
      const usernameLocalStorage = localStorage.getItem("username");
      console.log(usernameLocalStorage);
      if (usernameLocalStorage) {
        this.commit("LOGIN", usernameLocalStorage);
      }
    }
  },
  getters: {
    username: function(state) {
      return state.username;
    },
    loggedIn: function(state) {
      return state.loggedin;
    },
    getColor: function(state) {
      return state.themeColor;
    }
  }
});
