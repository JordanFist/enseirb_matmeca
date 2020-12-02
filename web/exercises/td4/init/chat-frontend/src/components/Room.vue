<template>
  <b-container class="mx-auto mt-3">
    <b-row>
      <b-col cols="4">
        <b-form v-on:submit.prevent="addMessage" v-on:reset.prevent="onReset">
          <b-form-group
            id="formInputGroup"
            label="Votre message :"
            label-for="content"
            description="Restez poli svp."
          >
            <b-form-textarea
              id="content"
              v-model="form.content"
              placeholder="Je ..."
              :rows="3"
              :max-rows="6"
            ></b-form-textarea>
          </b-form-group>
          <b-button type="submit" variant="primary">Envoyer</b-button>
          <b-button type="reset" variant="danger">Reset</b-button>
        </b-form>
      </b-col>
      <b-col cols="8">Liste des messages :
        <b-list-group class="mt-2">
          <b-list-group-item
            v-for="message in messages"
            v-bind:key="message.id"
            v-bind:class="{ right: message.author !== form.author }"
          >
          <message
          v-bind:username = "username"
          v-bind:message = "message"
          v-on:deleteMessage = "deleteMessage"
          >
          </message>
          </b-list-group-item>
        </b-list-group>
      </b-col>
    </b-row>
  </b-container>
</template>


<script>
import axios from "axios";
import store from "../store";
import Message from "./Message.vue";

export default {
  components: {
    Message
  },
  data: function() {
    return {
      form: {
        content: "",
        author: ""
      },
      messages: []
    };
  },
  computed: {
    username: function() {
      return this.$store.getters.username;
    },
    loggedIn() {
      return this.$store.getters.loggedin;
    }
  },
  methods: {
    addMessage: function(event) {
      axios
        .post("http://localhost:3000/messages", {
          author: this.username,
          content: this.form.content
        })
        .then(response => {
          this.loadMessages();
          this.form.content = "";
        })
        .catch(e => {
          console.error(e);
        });
    },
    onReset: function(evt) {
      this.form.content = "";
    },
    loadMessages: function() {
      axios
        .get("http://localhost:3000/messages")
        .then(response => {
          this.messages = response.data;
        })
        .catch(e => {
          console.error(e);
        });
    },
    deleteMessage: function(id) {
      axios
        .delete(`http://localhost:3000/messages/${id}`)
        .then(response => {
          this.loadMessages();
        })
        .catch(e => {
          console.error(e);
        });
    }
  },
  created: function() {
    this.loadMessages();
  }
};
</script>


<style>
.material-icons:hover {
  cursor: pointer;
}
.v-align {
  vertical-align: middle;
}
.right {
  text-align: right;
}
</style>

