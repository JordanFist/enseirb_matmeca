<template>
  <div class="mx-auto mt-3" style="width: 600px">
    <h2>Mon profil</h2>
    <hr>
    <h3>Mes préférences</h3>Thème de l'application :
    <select name="theme-color" id="theme-color" v-model="themeColor">
        <option value="primary">bleu</option>
        <option value="secondary">gris</option>
        <option value="success">vert</option>
        <option value="danger">rouge</option>
        <option value="warning">jaune</option>
        <option value="info">bleu turquoise</option>
        <option value="light">blanc</option>
        <option value="dark">noir</option>
    </select>
  </div>
</template>

<script>
import store from "../store";

export default {
  data() {
    return {
      themeColor: "info",
    };
  },
  watch: {
    themeColor: function(newColor, oldColor) {
      this.$store.dispatch("color", newColor);
    }
  }
};
</script>

<style>
</style>
