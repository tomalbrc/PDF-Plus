//
//  Util.h
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 29.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Util_h
#define Util_h

// Via https://stackoverflow.com/a/45892305/3374794
namespace PDF_Plus::VariantHelper {
	// Main lookup logic of looking up a type in a list.
	template<typename T, typename... ALL_T>
	struct isOneOf : public std::false_type {};
	
	template<typename T, typename FRONT_T, typename... REST_T>
	struct isOneOf<T, FRONT_T, REST_T...> : public
	std::conditional<
	std::is_same<T, FRONT_T>::value,
	std::true_type,
	isOneOf<T, REST_T...>
	>::type {};
	
	// Convenience wrapper for std::variant<>.
	template<typename T, typename VARIANT_T>
	struct isVariantMember;
	
	template<typename T, typename... ALL_T>
	struct isVariantMember<T, std::variant<ALL_T...>> : public isOneOf<T, ALL_T...> {};
}

#endif /* Util_h */
