// Copyright 2019 Ciobanu Bogdan-Calin
// bgdnkln@gmail.com

#pragma once

template <class info>
class circular_queue {
public:
    circular_queue(size_t _size = 10, bool _safety = true) { /// C-TOR
        size = _size;
        storage = new info[size];
        back_index = forward_index = 0;
        safety = _safety;
        load_factor = 0;
    };

    circular_queue(const circular_queue<info>& target) { /// COPY C-TOR
        *this = target;
    }

    [[gnu::hot]] void push(info target) {  /// SETTER
        if (safety == true)
            if (load_factor++ == size) {
                std::cout << "Queue integrity violation (1). Ignoring...\n";
                return;
            }
        storage[back_index] = target;

        cout << back_index << " " << target.first << endl;

        if (++back_index == size)
            back_index &= 0;
    }

    [[gnu::hot]] info pop() {  /// GETTER
        if (safety == true)
            if (load_factor-- == 0) {
                std::cout << "Queue integrity violation (2). Ignoring...\n";
                info null_statement;
                return null_statement;
            }
        unsigned aux = forward_index;

        if (++forward_index == size)
            forward_index &= 0;

        cout << aux << " ";
        return storage[aux];
    }

    circular_queue& operator = (const circular_queue<info>& target) { /// COPY ASSGN
        safety = target.safety;
        back_index = target.back_index;
        forward_index = target.forward_index;
        size = target.size;
        load_factor = target.load_factor;
        storage = new info[size];
        for (int i = 0; i < size; ++i)
            storage[i] = target.storage[i];
    }



    ~circular_queue() { /// D-TOR
        delete[] storage;
    }

private:
    info* storage;
    bool safety;
    unsigned back_index, forward_index, size, load_factor;
};