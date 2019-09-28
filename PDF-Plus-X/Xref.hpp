//
//  Xref.hpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 28.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Xref_hpp
#define Xref_hpp

#include <cstdio>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>


namespace PDF_Plus {
	class Object; // forwd. decl. needed (circular dep on Object and Xref (parent/child relationship), Object is templated)
	class ObjectRef;
	/**
	 
	 */
	class Xref {
	public:
		/**
		
		*/
		void add(Object* obj);
		
		/**
		
		*/
		void remove(Object* obj);
		
		/**
		 
		 */
		auto begin() const
		{
			return _objs.begin();
		}
		
		/**
		 
		 */
		auto end() const
		{
			return _objs.end();
		}
		
		/**
		 
		 */
		std::ostream& write(std::ostream& out, std::size_t headerOffset, const ObjectRef& docInfo) const;
		
	private:
		std::vector<Object*> _objs;
	};
}

#endif /* Xref_hpp */
