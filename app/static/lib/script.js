$(function () {
    var cvtNavButton = $('#cvt-nav-button');
    
    // When the CVT nav button is pressed...
    cvtNavButton.click(function(e){
        e.preventDefault();

        // ...show the cvt page.
        window.location.hash = 'cvt';
    });

    // On every hash change... 
    $(window).on('hashchange', function () {
        // ...the render function is called with the new hash.
        // This is how the navigation of our app happens.
        render(decodeURI(window.location.hash));
    });

    // This function decides what type of page to show 
    // depending on the current url hash value.
    function render(url) {
        // Get the keyword from the url.
        var key = url.split('/')[0];

        // Hide whatever page is currently shown.
        var page = $('.main-content .page');
        page.removeClass('visible');

        // page hashmap.
        var map = {
            // The Homepage.
            '': function() {
                renderHomePage();
            },

            // The CVT report page.
            '#cvt' : function() {
                renderCvtPage();
            }
        };

        // Execute the needed function depending on url keyword
        if(map[key]) {
            map[key]();
        } else {
            // show error page
            renderErrorPage();
        }
    }

    // Uses Handlebars to create a list of products using the provided data.
    // This function is called only once on page load.
    function generateAllCvtHTML(data) {
        
        var list = $('.cvt-report .cvt-list');
        var templateScript = $('#cvt-template').html();

        // compile template
        var template = Handlebars.compile(templateScript);
        list.append(template(data));
    }

    // Hides and shows products in the CVT report page depending on the data it recieves.
    function renderCvtPage(data) { 
        // get cvt data from API call...
        $.getJSON("api/cvt", function(data) {
            // generate the proper HTML...
            generateAllCvtHTML(data);

            var page = $('.cvt-report');
            page.addClass('visible'); 
        });
    }

    // Shows the Single Product Page with appropriate data.
    function renderHomePage() {
        var items = $('.cvt-report li');
        if (items) {
            items.remove();
        }
        
        var page = $('.home');
        page.addClass('visible');
    }

    // Shows the Error Page.
    function renderErrorPage() {
        // Shows the error page.
        var page = $('.error');
        page.addClass('visible');
    }

    // manually trigger a hashchange to start the app.
    $(window).trigger('hashchange');
});