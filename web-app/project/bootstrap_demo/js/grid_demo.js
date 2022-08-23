/* 
 * title: grid_demo.js
 * author: Jordan Breen
 */
const JUSTIFY_CONTENT_CLASSES = [
    'justify-content-start',
    'justify-content-end',
    'justify-content-center',
    'justify-content-between',
    'justify-content-around'
];
function is_number (_arg) {return typeof _arg === 'number';}
class Container {
    #html_element;
    #index;
    #content;
    constructor(_class = 'container', _index = 0, _content = '') {
        this.#html_element = document.createElement('div');
        this.html_class    = _class;
        this.#index        = _index;
        this.#content      = _content;
        this.#html_element.innerHTML = this.#content;
    }
    set html_class(_class) {
        this.#html_element.setAttribute('class', _class);
    }
    get html_element() {
        return this.#html_element;
    }
    get index() {
        return this.#index;
    }
}
class Column extends Container {
    static #MIN = 1;
    static #MAX = 12;
    static #NAME = 'col';
    static #BASE_CLASS = 'border border-dark bg-light fs-6 fw-bold text-center text-muted';
    #width;
    constructor(_index, _width = 1, _content = '') {
        super(Column.#NAME + '-' + _width + ' ' + Column.#BASE_CLASS, _index, _width);
        this.#width = _width;
    }
    get MIN() {return Column.#MIN;}
    get MAX() {return Column.#MAX;}
    static valid(_num) {return is_number(_num) && Column.#MIN <= _num && _num <= Column.#MAX;}
    get width() {
        return this.#width;
    }
}
class Row extends Container {
    static #MIN = 1;
    static #MAX = 20;
    static #NAME = 'row';
    static #BASE_CLASS = Row.#NAME;
    #columns;
    constructor(_column_widths, _index, _content = '', _justify = '') {
        super(Row.#BASE_CLASS, _index, _content);
        this.justify = _justify;
        const TOTAL_WIDTH = _column_widths.reduce((a, b) => a + b, 0);
        const NUM_COLUMNS = _column_widths.length;
        if(!Column.valid(TOTAL_WIDTH))
            throw new Error(`Invalid total column width (${TOTAL_WIDTH})`);
        this.#columns = [];
        for(let c = 0; c < NUM_COLUMNS; ++c) {
            this.#columns[c] = new Column(c, _column_widths[c]);
            this.html_element.appendChild(this.#columns[c].html_element);
        }
    }
    get MIN() {return Row.#MIN;}
    get MAX() {return Row.#MAX;}
    static valid(_num) {return is_number(_num) && Row.#MIN <= _num && _num <= Row.#MAX;}
    set justify(_justify) {
        this.html_class = Row.#BASE_CLASS + ' ' + _justify;
    }
}
class Grid {
    #container;
    #rows;
    constructor(_row_data) {
        const NUM_ROWS = _row_data.length;
        if(!Row.valid(NUM_ROWS))
            throw new Error(`Invalid number of rows (${NUM_ROWS})`);
        this.#container = new Container();
        this.#rows      = [];
        for(let r = 0; r < _row_data.length; ++r) {
            this.#rows[r] = new Row(_row_data[r], r);
            this.#container.html_element.appendChild(this.#rows[r].html_element);
        }
    }
    get container() {
        return this.#container;
    }
    set justify(_justify) {
        for(const row of this.#rows) 
            row.justify = _justify;
    }
}

$(document).ready(function() {
    const GRID_DEMO = document.getElementById('grid_demo');
    const JUSTIFIER = document.getElementById('justification_select');
    const GRID = new Grid([
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], 
        [2, 2, 2, 2, 2, 2], 
        [3, 3, 3, 3], 
        [4, 4, 4],
        [5, 5],
        [6, 6],
        [7],
        [8],
        [9],
        [10],
        [11],
        [12],
        [1, 1, 1, 1, 1, 1],
        [1, 1, 1, 1],
        [1, 1],
        [2, 2, 2, 2],
        [2, 2, 2],
        [2, 2],
        [2],
    ]);
    JUSTIFIER.grid = GRID;
    GRID_DEMO.appendChild(GRID.container.html_element);
    JUSTIFIER.addEventListener('change', (event) => {
        event.target.grid.justify = `justify-content-${event.target.value}`;
    });
});