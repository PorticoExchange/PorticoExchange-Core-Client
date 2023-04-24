// Fabric Dependencies
const Service = require('@fabric/core/types/service/lightning');

// Class Definition
class lightning {
  constructor (input = {}) {
    // Mandatory
    super(input);

    // Try to configure, else return null
    try {
      // Apply the input to some defaults
      this.settings = Object.assign({
        clock: 0,    // vector clock start
        frequency: 1 // Hz
      }, input);
    } catch (exception) {
      // Failed to apply input to an object {}...
      // Maybe we should switch to TypeScript? ;)
      console.error('Could not create MyService:', exception);
      return null;
    }

    // Currently mandatory
    // TODO: make optional
    this._state = {
      content: null
    };

    // Chainable pattern
    return this;
  }

  // Called once per 
  tick () {
    const origin = this.get('clock');
    console.log('clock:', origin);
    this.set('clock', origin++);
    this.
  }

  // custom start function
  // you can obviously call `super.start()` and `super.stop()`
  // but this is an example :) and we haven't fully defined expected behaviors yet!
  async start () {
    // super.start(); // disabled for clean example
    
  }
}
