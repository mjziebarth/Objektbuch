/*
 * Metaprogramming types.
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

#ifndef OBJEKTBUCH_META_HPP
#define OBJEKTBUCH_META_HPP

#include <memory>

namespace objektbuch {

/*
 * Transform a set of types to a set of shared_ptr of
 * the same type.
 */
template<typename... Objects>
struct to_shared_ptr_variants;


template<typename O, typename... Objects>
struct to_shared_ptr_variants<O, Objects...>
{
    using type = std::decay_t<
        decltype(
            std::tuple_cat(
                std::declval<std::tuple<std::shared_ptr<O>>>(),
                std::declval<typename to_shared_ptr_variants<Objects...>::type>()
            )
        )
    >;
};

template<typename O>
struct to_shared_ptr_variants<O>
{
    using type = std::tuple<std::shared_ptr<O>>;
};

template<typename... Objects>
using to_shared_ptr_variants_t = typename to_shared_ptr_variants<Objects...>::type;

/*
 * Transform a tuple of types to a variant of the same types.
 */
template<typename... T>
struct tuple_to_variant;

template<typename... T>
struct tuple_to_variant<std::tuple<T...>>
{
    using type = std::variant<T...>;
};

template<typename... T>
using tuple_to_variant_t = typename tuple_to_variant<T...>::type;


/*
 * Ensure that a type is part of a template parameter pack.
 */
template<typename Tq, typename... T>
struct contains_type;

template<typename Tq, typename T0, typename... T>
struct contains_type<Tq, T0, T...>
{
    constexpr static bool value =
        std::is_same_v<T0, Tq>
        || contains_type<Tq, T...>::value;
};

template<typename Tq, typename T0>
struct contains_type<Tq, T0>
{
    constexpr static bool value = std::is_same_v<T0, Tq>;
};

template<typename Tq, typename... T>
constexpr bool contains_type_v = contains_type<Tq, T...>::value;
}

#endif