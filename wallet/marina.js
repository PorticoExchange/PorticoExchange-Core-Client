import { detectProvider } from 'marina-provider';

try {
  const marina = await detectProvider('marina');
  initApp(marina); // initialize your app
} catch (err) {
  console.log('Please install Marina extension!');
}
