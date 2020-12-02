'use strict';

const apiKey = 'd367d2b32c6effdcff8407f35c63c1d7';
// const apiKey = '7aa887c381f3021f19462c39c14c98ee';
const apiUrl = 'http://api.openweathermap.org/data/2.5/forecast?units=metric&lang=fr&appid=' + apiKey + '&q=';
const iconUrl = 'http://openweathermap.org/img/w/';

const days = ['Dimanche', 'Lundi', 'Mardi', 'Mercredi', 'Jeudi', 'Vendredi', 'Samedi'];

function computeDayFromDatetime(datetime) {
    // Transformation en millisecondes
}

function render(cityName, weatherToShow) {

    // Affichage de la ville

    // Création des blocs pour chaque jour

}

function handleData(data) {
    // Récupération du nom de la ville

    var cityName = data.city.name;
    // Parcours des données reçues

    console.log(data.list[0].dt);
    var date;
    var temperature;


    
}

//Nouvelle méthode
function searchWeather(event) {
    event.preventDefault();
    
    var c = document.getElementById("city");
    var lien = apiUrl + c.value;

    fetch(lien)
        .then(data=>data.json())
        //.then(data=>console.log(data))
        .then(data=>handleData(data))
        .catch(error=>console.log(error))
    //console.log("toto");
    
}

/* Ancienne méthode
function searchWeather(event) {

    // Prévention de la soumission du formulaire

    event.preventDefault(); //permet de ne pas rafraichir la page
    
    // Récupération du champ city renseigné par l'utilisateur

    var c = document.getElementById("city");
    var lien = apiUrl + c.value;
    
    // Appel avec Ajax (XMLHttpRequest)
    
    const req = new XMLHttpRequest();
    req.open('GET', lien, false);
    req.send(null);
    if (req.status === 200) {
        console.log("Réponse reçue: %s", req.responseText);
    } else {
        console.log("Status de la réponse: %d (%s)", req.status, req.statusText);
    }
    let data = JSON.parse(req.responseText);
    console.log(data);
}*/