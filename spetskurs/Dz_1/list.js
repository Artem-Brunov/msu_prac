function Element(data)
{
    this.data = data;
    this.next = null;
    this.prev = null;
}

function Double_list()
{
    this._length = 0;
    this.head = null;
    this.tail = null;
}

Double_list.prototype.add = function(data)
{
    var element = new Element(data);

    if(this._length)
    {
        this.tail.next = element;
        element.prev = this.tail;
        this.tail = element;
    }
    else
    {
        this.head = element;
        this.tail = element;
    }

    this._length++;

    return element;
};

Double_list.prototype.search = function(position)
{
    var n_element = this.head;
    var length = this._length;
    var i = 1;
    var err = {failure: 'Failure: index out of range'}

    if(length == 0 || position < 1 || position > length)
    {
        throw new Error(err.failure);
    }

    while(i < position)
    {
        n_element = n_element.next;
        i++;
    }

    return n_element;
};

Double_list.prototype.remove = function(position)
{
    var n_element = this.head, length = this._length, i = 1, err = {failure: 'Failure: index out of range'},
        buffer_1 = null, buffer_2 = null;

    if (length == 0 || position < 1 || position > length)
    {
        throw new Error(err.failure);
    }

    if (position == 1)
    {
        this.head = n_element.next;

        if (!this.head)
        {
            this.head.prev = null;
        }
        else
        {
            this.tail = null;
        }

    }
    else if (position == this._length)
    {
        this.tail = this.tail.prev;
        this.tail.next = null;

    }
    else
    {
        while (i < position)
        {
            n_element = n_element.next;
            i++;
        }

        buffer_1 = n_element.prev;
        buffer_2 = n_element.next;

        buffer_1.next = buffer_2;
        buffer_2.previous = buffer_1;
        n_element = null;
    }

    this._length--;

};

function creater(number)
{
    number = String(number);
    var i = 0;
    while (i < number.length)
    {
        parseInt(number[i], 10) = Double_list.add;
    }
}