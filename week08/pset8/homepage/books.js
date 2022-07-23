// Section variables
booksTag = document.querySelector('#books-list');
booksInfo = document.querySelector('#book');


// BOOKS
// Three Body Problem
document.querySelector('#three-a').addEventListener('click', function()
{
    document.getElementById('book-title').innerHTML = 'The Three Body Problem Trilogy';
    document.getElementById('book-description').innerHTML = "Set against the backdrop of China's Cultural Revolution, a secret military project sends signals into space to establish contact with aliens. An alien civilization on the brink of destruction captures the signal and plans to invade Earth. Meanwhile, on Earth, different camps start forming, planning to either welcome the superior beings and help them take over a world seen as corrupt, or to fight against the invasion. The result is a science fiction masterpiece of enormous scope and vision.";
    booksTag.style.backgroundColor = 'rgba(5, 5, 25)';
    booksInfo.style.backgroundImage = 'url(https://cdnb.artstation.com/p/assets/images/images/025/430/367/large/mateusz-ambrozewicz-droplet2020.jpg?1585764522)'
});

// Hyperion
document.querySelector('#hyper-a').addEventListener('click', function()
{
    document.getElementById('book-title').innerHTML = 'Hyperion';
    document.getElementById('book-description').innerHTML = "On the world called Hyperion, beyond the law of the Hegemony of Man, there waits the creature called the Shrike. There are those who worship it. There are those who fear it. And there are those who have vowed to destroy it. In the Valley of the Time Tombs, where huge, brooding structures move backward through time, the Shrike waits for them all. On the eve of Armageddon, with the entire galaxy at war, seven pilgrims set forth on a final voyage to Hyperion seeking the answers to the unsolved riddles of their lives. Each carries a desperate hope—and a terrible secret. And one may hold the fate of humanity in his hands.";
    booksTag.style.backgroundColor = 'rgb(94,44,95)';
    booksInfo.style.backgroundImage = 'url(https://www.aureliuzrex.com/content/images/size/w2000/2022/01/hyperion_blog_101.png)'
});

// Dune
document.querySelector('#dune-a').addEventListener('click', function()
{
    document.getElementById('book-title').innerHTML = 'Dune';
    document.getElementById('book-description').innerHTML = "Set on the desert planet Arrakis, Dune is the story of the boy Paul Atreides, heir to a noble family tasked with ruling an inhospitable world where the only thing of value is the “spice” melange, a drug capable of extending life and enhancing consciousness. Coveted across the known universe, melange is a prize worth killing for...";
    booksTag.style.backgroundColor = 'rgb(110,70,45)';
    booksInfo.style.backgroundImage = 'url(https://pro2-bar-s3-cdn-cf6.myportfolio.com/1106a126cb8c279c74f2a01a8c318f38/06480e1b798bc8cac4345f818f4d13573cf974faaa59f1bd15a3c672c451224167cdd3ad880ad290_rw_1920.jpg?h=68695a1f014c33e1c37b4fa4f6f4a89e)'
});