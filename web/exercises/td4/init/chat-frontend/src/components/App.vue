<template>
  <div id="app">
    <b-navbar toggleable="md" type="dark" variant="info">
      <b-navbar-toggle target="nav_collapse"></b-navbar-toggle>

      <b-navbar-brand to="/">Chat Enseirb</b-navbar-brand>

      <b-collapse is-nav id="nav_collapse">
        <b-navbar-nav>
          <b-nav-item v-if="loggedIn">Salon de discussion</b-nav-item>
        </b-navbar-nav>
        <b-navbar-nav>
          <b-nav-item to="/room">Salon de discussion</b-nav-item>
        </b-navbar-nav>
        <b-navbar-nav class="ml-auto">
          <b-nav-item v-if="!loggedIn" to="/login">Se connecter</b-nav-item>
          <b-nav-item v-else v-on:click="logout">Se déconnecter</b-nav-item>
        </b-navbar-nav>
      </b-collapse>
    </b-navbar>

    <!-- Contenu du site -->
    <router-view></router-view>
  </div>
</template>

<script>
import store from "../store";

export default {
  components: {},
  methods: {
    logout: function(event) {
      this.$store.dispatch("logout");
      this.$router.push("/");
    }
  },
  computed: {
    loggedIn() {
      return this.$store.getters.loggedIn;
    }
  }
};
</script>

<style>
</style>
