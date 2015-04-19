#ifndef WEIGHTED_LIST_H
#define WEIGHTED_LIST_H

#include "rng.h"
#include <vector>

template <typename T> struct weighted_obect {
    T obj;
    int weight;
};

template <typename T> struct weighted_list {
    weighted_list() : total_weight(0) { };

    /**
     * This will add a new object to the weighted list.
     * @param obj The object that will be added to the list.
     * @param weight The weight of the object.
     */
    void add_item(T obj, int weight) {
        if(weight >= 0) {
            weighted_obect<T> new_weighted = { obj, weight };
            objects.push_back(new_weighted);
            total_weight += weight;
        }
    }

    /**
     * This will check to see if the given object is already in the weighted
       list. If it is, we update its weight with the new weight value. If it
       is not, we add it normally.
     * @param obj The object that will be updated or added to the list.
     * @param weight The new weight of the object.
     */
    void add_or_replace_item(T obj, int weight) {
        if(weight >= 0) {
            for(auto &itr : objects) {
                if(itr.obj == obj) {
                    total_weight += (weight - itr.weight);
                    itr.weight = weight;
                    return;
                }
            }

            // if not found, add to end of list
            add_item(obj, weight);
        }
    }

    /**
     * This will call the given callback function once for every object in the weighted list.
     * @param func The callback function.
     */
    void apply(void (*func)(T &obj)) {
        for(auto &itr : objects) {
            func(itr.obj);
        }
    }

    /**
     * This will return a pointer to an object from the list randomly selected
     * and biased by weight. If the weighted list is empty or all items in it
     * have a weight of zero, it will return a NULL pointer.
     */
    T* pick() {
        if(total_weight > 0) {
            return &(objects[pick_ent()].obj);
        }
        else {
            return NULL;
        }
    }

    /**
     * This will remove all objects from the list.
     */
    void clear() {
        total_weight = 0;
        objects.clear();
    }

    /**
     * This will return the sum of all the object's weights in the list.
     */
    int get_weight() {
        return total_weight;
    }

private:
    int total_weight;
    std::vector<weighted_obect<T> > objects;

    size_t pick_ent() {
        int picked = rng(0, total_weight);
        int accumulated_weight = 0;
        size_t i;
        for(i=0; i<objects.size(); i++) {
            accumulated_weight += objects[i].weight;
            if(accumulated_weight >= picked) {
                break;
            }
        }
        return i;
    }
};

#endif
