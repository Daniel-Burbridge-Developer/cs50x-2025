// Easter egg: Click the CS50x title to change its color
document.addEventListener('DOMContentLoaded', function() {
    const title = document.querySelector('.display-1');
    
    // Array of colors to cycle through
    const colors = ['red', 'blue', 'green', 'purple', 'orange', 'pink', 'teal'];
    
    title.addEventListener('click', function() {
        // Pick a random color from the array
        const randomIndex = Math.floor(Math.random() * colors.length);
        const randomColor = colors[randomIndex];
        
        // Apply color and add bounce animation
        title.style.color = randomColor;
        title.style.transform = 'scale(1.1)';
        
        // Reset scale after animation
        setTimeout(function() {
            title.style.transform = 'scale(1)';
        }, 200);
    });
    
    // Add cursor pointer to indicate it's clickable
    title.style.cursor = 'pointer';
    title.style.transition = 'transform 0.2s ease';
});
