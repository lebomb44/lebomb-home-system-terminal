$(document).ready(function() {

    // retenir le cookie
    var options_cookies = {
        expiresAt: new Date(2011, 1, 1)
    };

    var string_remote = 'Précisez le code de votre Freebox qui se trouve dans les paramètres généraux sur la TV';
    // voir si code en cookies
    var remotekey = '37996978'; // frenes='77674595' viala='37996978'; // $.cookies.get('remotekey');
    if(remotekey==null) {
        var remotekey = prompt(string_remote,'');
        if(remotekey!=null) {
            $.cookies.set('remotekey',remotekey, options_cookies);
        }
    }

    // url de l'API
    var url_api = 'http://lebomb.no-ip.com/cgi/freebox.cgi?code='+remotekey+'&key=';
    //var url_api = 'http://hd1.freebox.fr/pub/remote_control?code='+remotekey+'&key=';

    // fichier des chaines
    var url_channels = 'channels/channels.json';
    
    // charger les chaines
    $.ajax({
        url: url_channels,
        dataType: 'json',
        success: function(msg) {
            $.each(msg, function(i,item){
                $('#listchannels').append('<li id="channel'+item.id+'"><a href="'+item.id+'">'+item.name+'</a></li>');
            });
            // click sur une des chaines de la liste
            $('#listchannels li a').click(function() {
                var key = $(this).attr("href");
                keys = key+''.split();
                for(var i=0;i<keys.length;i++){
                    $('#channel'+key+' a').addClass('.loading');
                    var longPush='true';
                    if(i==(keys.length-1)) {
                        longPush='false';
                    }
                    $.ajax({ 
                        url: url_api + keys[i] + '&long=' + longPush,
                        /*beforeSend: function() {
                            $('#channel'+key+' a').addClass('.loading');
                        },
                        success: function() {
                            $('#channel'+key+' a').removeClass('.loading');
                        }*/
                    });
                }
                $('#channel'+key+' a').removeClass('.loading');
                return false;
            });
        }
    });

    // click télécommande
    $('#telecommande li a').click(function(event) {
        event.preventDefault();
        var key = $(this).attr("href");
        // liste des chaines
        if(key.toString()=='list') {
            $('#telecommande').slideUp('slow');
            $('#channelslist').removeClass('hide').slideDown('slow');
            return false;
        }
        // infos sur moi
        if(key.toString()=='media') {
            key = 'mail&long=true';
        }
        // infos sur moi
        if(key.toString()=='linkkey') {
            $('#telecommande').slideUp('slow');
            $('#infosblock').removeClass('hide').slideDown('slow');
            return false;
        }
        $.ajax({
            url: url_api + key
        });
        return false;
    });

    // click sur retour depuis la liste des chaines
    $('.backbutton a').click(function() {
        var divclose = $(this).attr('rel');
        $('#'+divclose).slideUp('slow').addClass('hide');
        $('#telecommande').slideDown('slow');
        return false;
    });

    // click sur le bouton code
    $('#remotekey a').click(function() {
        var remotekey = prompt(string_remote,'');
        if(remotekey!=null) {
            $.cookies.set('remotekey',remotekey, options_cookies);
        }
    });

});
