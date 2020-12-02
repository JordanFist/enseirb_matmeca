<template>
  <div>
    <template v-if="message.author == username">
      <b-badge variant="primary">{{message.author}}</b-badge>
      {{message.content}}
    </template>
    <template v-else>
      {{message.content}}
      <b-badge variant="info">{{message.author}}</b-badge>
    </template>
    <i
      class="material-icons v-align"
      v-on:click="$emit('deleteMessage', id)"
      v-if="message.author == username"
    >delete</i>
  </div>
</template>


<script>
export default {
  name: "message",
  props: {
      message: Object,
      username: String,
  }
};
</script>