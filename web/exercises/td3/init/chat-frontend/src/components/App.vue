<template>
  <div id="app">
    <b-navbar toggleable="md" type="dark" variant="info" class="mb-4">
      <b-navbar-toggle target="nav_collapse"></b-navbar-toggle>

      <b-navbar-brand to="/">Chat Enseirb</b-navbar-brand>
    </b-navbar>
    <b-container>
      <b-row>
        <b-col cols="4">
          <b-form v-on:submit.prevent="addMessage" v-on:reset.prevent="onReset">
            <b-form-group id="author" label="Votre nom :" label-for="author">
              <b-form-input id="author" v-model="form.author"></b-form-input>
            </b-form-group>
            <b-form-group
              id="content"
              label="Votre message :"
              label-for="content"
              description="Restez poli svp."
            >
              <b-form-textarea
                id="content"
                v-model="form.content"
                placeholder="Je ..."
                :rows="6"
                :max-rows="6"
              ></b-form-textarea>
            </b-form-group>
            <b-button type="submit" variant="primary">Envoyer</b-button>
            <b-button type="reset" variant="danger">Reset</b-button>
          </b-form>
          <b-button variant="info" v-on:click="generateMessages" class="mt-2">Générer des messages</b-button>
        </b-col>
        <b-col cols="8">Liste des messages :
          <b-list-group>
            <b-list-group-item
              v-for="message in messages"
              :key="message.id"
              v-bind:class="{ right: message.author !== form.author }"
            >
              <template v-if="message.author == form.author">
                <b-badge variant="secondary">{{message.author}}</b-badge>
                {{message.content}}
                <br>
                <span class="small">{{message.createdAt | moment("DD/MM/YY - HH:mm")}}</span>
                <i class="material-icons v-align" v-on:click="deleteMessage(message.id)">delete</i>
              </template>
              <template v-else>
                {{message.content}}
                <b-badge variant="info">{{message.author}}</b-badge>
                <br>
                <span class="small">{{message.createdAt | moment("DD/MM/YY - HH:mm")}}</span>
              </template>
            </b-list-group-item>
          </b-list-group>
        </b-col>
      </b-row>
    </b-container>
  </div>
</template>

<script>
import axios from "axios";

export default {
  data: function() {
    return {
      form: {
        content: "",
        author: ""
      },
      messages: []
    };
  },
  methods: {
    addMessage: function(event) {
      axios
        .post("http://localhost:3000/messages", {
          author: this.form.author,
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
      this.form.author = "";
      this.form.content = "";
    },
    loadMessages: function() {
      axios
        .get("http://localhost:3000/messages")
        .then(response => {
          this.messages = response.data.slice(0, 10);
        })
        .catch(e => {
          console.error(e);
        });
    },
    deleteMessage: function(id) {
      axios
        .delete(`http://localhost:3000/messages/${id}`)
        .then(response => {
          //this.loadMessages();
          this.messages = this.messages.filter(m => m.id !== id);
        })
        .catch(e => {
          console.error(e);
        });
    },
    generateMessages: function() {
      axios
        .post(`http://localhost:3000/messages/generate`)
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


<style scoped>
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

