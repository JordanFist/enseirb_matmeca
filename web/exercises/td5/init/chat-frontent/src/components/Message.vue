<template>
  <b-list-group-item>
    <template v-if="message.author == username">
      <b-badge variant="primary">{{message.author}}</b-badge>
      {{message.content}}
      <br>
      <span class="small">{{message.createdAt | moment("DD/MM/YY - HH:mm")}}</span>
    </template>
    <template v-else>
      {{message.content}}
      <b-badge variant="info">{{message.author}}</b-badge>
      <br>
      <span class="small">{{message.createdAt | moment("DD/MM/YY - HH:mm")}}</span>
    </template>
    <i
      class="material-icons v-align"
      v-on:click="$emit('deleteMessage', message.id)"
      v-if="message.author == username"
    >delete</i>
  </b-list-group-item>
</template>

<script>
export default {
  name: "Message",
  props: ["username", "message"]
};
</script>
