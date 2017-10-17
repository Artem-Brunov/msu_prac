function transform(string)
{
    if(!parseInt(string))
        return;
    var ansver = 0;
    var j = string.length;
    for(var i = 0; i < string.length; i++)
    {
        ansver = ansver + parseInt(string[j - 1 - i], 10) * Math.pow(2, i);
    }
    return ansver;
}
