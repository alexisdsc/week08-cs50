// Section variables
navTag = document.querySelector('#games-list');
gameInfo = document.querySelector('#game');

// GAMES
// spiderman case
document.querySelector('#spiderman-a').addEventListener('click', function()
{
    document.getElementById('game-title').innerHTML = 'Marvel: Spider-Man';
    document.getElementById('game-description').innerHTML = "The game follows Peter Parker, a 23-year-old college graduate and research assistant who gained superhuman abilities after being bitten by a radioactive spider. Peter is in his eighth year of crime-fighting under his super heroic alter ego of Spider-Man, who has become highly experienced at this point, but struggles to balance his superhero and personal lives.";
    navTag.style.backgroundColor = 'rgba(100,30,30)';
    gameInfo.style.backgroundImage = 'url(https://i.blogs.es/aa759f/spiderman0/1366_2000.jpg)'
});

// breath of the wild case
document.querySelector('#zelda-a').addEventListener('click', function()
{
    document.getElementById('game-title').innerHTML = 'The Legend of Zelda: Breath of the Wild';
    document.getElementById('game-description').innerHTML = "One of the best Games of the world, the protagonist, Link, wakes up in a world he remembers nothing about. Now he must to explore this huge and misterious world to find a way to recover his dreams before it's too late.";
    navTag.style.backgroundColor = 'rgba(10, 30, 15)';
    gameInfo.style.backgroundImage = 'url(https://wallpapercave.com/wp/wp1913622.jpg)'
});

// Ghost of Tsushima case
document.querySelector('#ghost-a').addEventListener('click', function()
{
    document.getElementById('game-title').innerHTML = 'Ghost of Tsushima';
    document.getElementById('game-description').innerHTML = "Ghost of Tsushima is a third-person open-world action-stealth video game developed by Sucker Punch Productions exclusively for the PlayStation 4. It takes place in 1274 on the island of Tsushima in Japan. The player controls the hero, Jin Sakai, as he fights back against a Mongol invasion.";
    navTag.style.backgroundColor = 'rgba(10,20,40)';
    gameInfo.style.backgroundImage = 'url(https://i.pinimg.com/originals/92/8f/be/928fbed6ffb6bae828eed5b3378b7106.jpg)'
});
