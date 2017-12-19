$(function(){
    $('#myButton').bind( 'click', printt);
});
$(function(){
    $('#myButton_2').bind( 'click', search);
});
function printt() {
    document.getElementById('take_2').innerHTML = $("#EngW").val();
    
}
function search() {
    document.getElementById('take_2').innerHTML = $("#EngW").val();
    $("#take_2").find($($("#ListName").val())).css('background-color', 'Orchid');
}