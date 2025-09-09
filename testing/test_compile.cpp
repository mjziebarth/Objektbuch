/*
 * A simple compile test.
 *
 * Author: Malte J. Ziebarth (malte.ziebarth@tum.de)
 *
 * Copyright (C) 2025 Technische Universität München
 *
 * Licensed under the EUPL, Version 1.2 or – as soon they will be approved by
 * the European Commission - subsequent versions of the EUPL (the "Licence");
 * You may not use this work except in compliance with the Licence.
 * You may obtain a copy of the Licence at:
 *
 * https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the Licence is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the Licence for the specific language governing permissions and
 * limitations under the Licence.
 */

#include <string>
#include <iostream>
#include <objektbuch/objectbook.hpp>

using ObjectBook = objektbuch::ObjectBook<size_t, const char*, double, std::string>;

ObjectBook objects;

int main()
{
    const char* message = "A message!\n";
    size_t msg_id = objects.emplace(&*(message));
    size_t d_id = objects.emplace(1.235);

    /* Obtain the message from the wrong ID: */
    try {
        std::cout << objects.get<const char*>(d_id);
        std::cerr << "Converted something that should not be converted...\n";
        return 1;
    } catch (...){
        /* We expect an error here! */
    }

    /* Now obtain the message from the right ID: */
    try {
        std::cout << objects.get<const char*>(msg_id);
    } catch (...){
        std::cerr << "Could not convert the string message from its ID.\n";
        return 1;
    }
    return 0;
}