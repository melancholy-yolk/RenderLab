#ifndef _BASIC_HEADER_ARRAY_2D_H_
#define _BASIC_HEADER_ARRAY_2D_H_

#include <array>

namespace CppUtil {
	namespace Basic {
		template<typename T, int W, int H>
		class Array2D {
		public:
			static constexpr int width = W;
			static constexpr int height = H;
			static constexpr int size = W * H;

		public:
			T & At(int x, int y) { return this->operator()(x, y); }
			T & operator()(int x, int y){
				assert(x >= 0 && x < W - 1);
				assert(y >= 0 && y < H - 1);
				return data[y * W + x];
			}

			const T * GetData() const & { data.data(); }
			T * GetData() & { data.data(); }

		private:
			std::array<T, W*H> data;
		};
	}
}

#endif // !_BASIC_HEADER_ARRAY_2D_H_
