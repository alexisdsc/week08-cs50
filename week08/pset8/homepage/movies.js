// Section variables
moviesTag = document.querySelector('#movies-list');
movieInfo = document.querySelector('#movie');


// MOVIES
// Interstellar case
document.querySelector('#inter-a').addEventListener('click', function()
{
    document.getElementById('movie-title').innerHTML = 'Interstellar';
    document.getElementById('movie-description').innerHTML = 'Interstellar is my in my top must-watch movies because mix in a well manner the cinema with science. It is about a group of explorers jumping through wormholes searching the way to save the humankind.';
    moviesTag.style.backgroundColor = 'rgba(5, 5, 25)';
    movieInfo.style.backgroundImage = 'url(https://gurumed-oxn8moh.netdna-ssl.com/wp-content/uploads/2014/10/interstellar-trou-noir.png)'
});

// Blade Runner
document.querySelector('#runner-a').addEventListener('click', function()
{
    document.getElementById('movie-title').innerHTML = 'Blade Runner 2049';
    document.getElementById('movie-description').innerHTML = "Young Blade Runner K's discovery of a long-buried secret leads him to track down former Blade Runner Rick Deckard, who's been missing for thirty years. This movie is sequel of the movie 'Blade Runner' but you can watch this without the necessity of watch the previous one.";
    moviesTag.style.backgroundColor = 'rgb(29,14,43)';
    movieInfo.style.backgroundImage = 'url(https://img3.wallspic.com/previews/7/0/3/4/5/154307/154307-luz-blade_runner_2049-jueves-morado-entretenimiento-x750.jpg)'
});

// Dune
document.querySelector('#dunemovie-a').addEventListener('click', function()
{
    document.getElementById('movie-title').innerHTML = 'Dune';
    document.getElementById('movie-description').innerHTML = "Dune is the latest masterpiece of the science fiction movies. In this movie a noble family becomes embroiled in a war for control over the galaxy's most valuable asset while its heir becomes troubled by visions of a dark future.";
    moviesTag.style.backgroundColor = 'rgb(110,70,45)';
    movieInfo.style.backgroundImage = 'url(https://images.surfacemag.com/app/uploads/2021/10/26180457/dune-2021-remake-02.jpg)'
});