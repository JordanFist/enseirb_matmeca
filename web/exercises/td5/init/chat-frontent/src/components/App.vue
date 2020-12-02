<template>
  <div id="app">
    <b-navbar toggleable="md" type="dark" v-bind:variant="themeColor">
      <b-navbar-toggle target="nav_collapse"></b-navbar-toggle>

      <b-navbar-brand to="/">Chat Enseirb</b-navbar-brand>

      <b-collapse is-nav id="nav_collapse">
        <b-navbar-nav>
          <b-nav-item v-if="loggedIn" to="/room">Salon de discussion</b-nav-item>
        </b-navbar-nav>
        <b-navbar-nav v-if="!loggedIn" class="ml-auto">
          <b-nav-item to="/login">Se connecter</b-nav-item>
        </b-navbar-nav>
        <b-navbar-nav v-else class="ml-auto">
          <b-nav-item to="/profile">Mon profil</b-nav-item>
          <b-nav-item v-on:click="logout">Se déconnecter</b-nav-item>
        </b-navbar-nav>
      </b-collapse>
    </b-navbar>
    <router-view></router-view>
  </div>
</template>

<script>
import store from "../store";

export default {
  methods: {
    logout: function(event) {
      this.$store.dispatch("logout");
      this.$router.push("/");
    }
  },
  computed: {
    themeColor: function() {
      return this.$store.getters.getColor;
    },
    loggedIn() {
      return this.$store.getters.loggedIn;
    }
  },
  mounted() {
    this.$store.dispatch("init");
  }
};
</script>

<style>
</style>
