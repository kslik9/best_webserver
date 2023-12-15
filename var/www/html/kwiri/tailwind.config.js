/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    "./*.*"
  ],
  theme: {
    screens: {
      'tablet': '640px',
      // => @media (min-width: 640px) { ... }

      'laptop': '1024px',
      // => @media (min-width: 1024px) { ... }

      'desktop': '1280px',
      // => @media (min-width: 1280px) { ... }
    },
    fontFamily: {
      'arabic': ['Cairo', 'sans-serif'],
    },
    extend: {
      gridTemplateRows: {
        // Simple 8 row grid
        '1': 'repeat(1, minmax(0, auto))',
        // Simple 8 row grid
        '2': 'repeat(2, minmax(0, auto))',
        // Simple 8 row grid
        '3': 'repeat(3, minmax(0, auto))',
        // Simple 8 row grid
        '4': 'repeat(4, minmax(0, auto))',
        // Simple 8 row grid
        '5': 'repeat(5, minmax(0, auto))',
        // Simple 8 row grid
        '6': 'repeat(6, minmax(0, auto))',
        // Simple 8 row grid
        '7': 'repeat(7, minmax(0, auto))',
        // Simple 8 row grid
        '8': 'repeat(8, minmax(0, auto))',
      }
    },
  },
  plugins: [],
}
