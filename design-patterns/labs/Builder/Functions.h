#pragma once

#include "FileReader.h"
#include "Dish.h"
#include "MenuItem.h"
#include <string>

MenuItem* CreateMenuItem(const std::string fileName){
	FileReader fr = FileReader(fileName);
	fr.Read();
	FullInfo data = fr.Data();
	
	MenuItem* item = new MenuItem();
	item->SetName(data.name);
	item->SetPrice(data.price);
	item->SetTax(data.tax);
	
	
    const char* const delim = ", ";

    std::ostringstream imploded;
    std::copy(data.ingredients.begin(), data.ingredients.end(),
        std::ostream_iterator<std::string>(imploded, delim)
    );
	
    item->SetIngredients(imploded.str());
    return item;
}

Dish* CreateDish(const std::string fileName){
	FileReader fr = FileReader(fileName);
	fr.Read();
	FullInfo data = fr.Data();
	
	Dish* item = new Dish();
    item->SetName(data.name);
    item->SetCallories(data.callories);
    item->SetOrigin(data.origin);
    item->SetReceipe(data.receipe);
    item->SetIngredients(data.ingredients);
    return item;
}
