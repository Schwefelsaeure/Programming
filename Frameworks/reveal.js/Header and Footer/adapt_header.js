// Fill in left header with frametitle
Reveal.on( 'slidechanged', event => {
    // event.previousSlide, event.currentSlide, event.indexh, event.indexv
    let headerLeft = document.querySelector(".reveal .header-left");
    headerLeft.innerHTML = event.currentSlide.title;
} );

// Fill in footer with current part and all sections of this part
Reveal.on( 'slidechanged', event => {
    // event.previousSlide, event.currentSlide, event.indexh, event.indexv
    // TODO Query parent horizontal slide, extract "name" and fill footer
    // Then, query vertical slides and make dots for each vertical slide
    let parts = document.querySelectorAll(".reveal .slides section[type='part']");
    let footerLeft = document.querySelector(".reveal .footer");
    
    footerLeft.innerHTML = ""; // Clear footer
    
    for (let part of parts) {
        let divContainer = document.createElement("div");
        divContainer.innerHTML = part.getAttribute("name");
        divContainer.appendChild(document.createElement("br"));
        
        for (let slide of part.children) {
            let slideContainer = document.createElement("span");
            slideContainer.innerHTML = "x ";
            
            divContainer.appendChild(slideContainer);
        }
        
        footerLeft.appendChild(divContainer);
    }
    
} );
