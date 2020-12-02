'use strict;'

const express = require('express');
const faker = require('faker');
const cors = require('cors');
const bodyParser = require('body-parser');

const sqlite3 = require('sqlite3').verbose();
const Sequelize = require('sequelize');

// Initialisation serveur
const app = express();

// Configuration Faker
faker.locale = 'fr';

// Sécurité
app.use(cors());

// Configuration parser body
app.use(bodyParser.json());

// Route /

const db = new sqlite3.Database('database-chat.db');

db.run('DROP TABLE IF EXISTS message');
db.run('CREATE TABLE IF NOT EXISTS message (id INTEGER PRIMARY KEY AUTOINCREMENT, author TEXT, content TEXT, date TEXT)');

//GET method route

/*
app.get('/', function(req, res) {
  res.status(200).send('hello world');
});
*/

// GET method route

app.get('/messages', function(req, res) {
  const sql = "SELECT * from message ORDER BY date desc";

  db.all(sql, [], (err, rows) => {
    if (err)
    {
      throw err;
    }
    res.send(rows);
  });
});

// POST method route

app.post('/messages', function (req, res) {
  /*
  db.run(`INSERT INTO message(author, content, date) VALUES(?, ?,strftime('%Y-%m-%dT%H:%M')) "")`, [req.body.author, req.body.content], function(rr) {
    if (err) {
      return console.log(err.message);
    }
    console.log(`${this.lastID}`);
  } */
  res.status(201).send('POST request to the homepage');
});

app.post('/messages/generate', function (req, res) {
  res.status(201).send('POST request to the homepage');
});

app.delete('/messages/:id', function (req, res) {
  res.status(200).send('POST request to the homepage');
});

/* Partie SQLite */
// Connexion à la base de donnée avec sqlite


// Initialisation de la table message

// Récupération de tous les messages avec Sqlite

// Ajout d'un message avec Sqlite

// Génération de 10 messages aléatoires avec Sqlite

// Suppression d'un message avec Sqlite

/* Partie Sequelizer */

// Connexion à la base de donnée avec Sequelize
const sequelize = new Sequelize('sqlite:database-chat.db');


// Modèle Message avec Sequelize

// Création de la table

// Récupération de tous les messages avec Sequelizer

// Ajout d'un message avec Sequelizer

// Génération de 10 messages aléatoires avec Sequelizer

// Suppression d'un message avec Sequelizer

/* Démarrage serveur */
app.listen(3000, function () {
  console.log('Serveur chat-backend démarré !');
});
