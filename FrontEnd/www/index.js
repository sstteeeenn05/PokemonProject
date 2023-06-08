import './api/Alpine.js'

document.addEventListener('alpine:init', ()=>{
  Alpine.store('home', {

  })
})

document.addEventListener('alpine:init', ()=>{
  Alpine.store('modal', {
    pokemonLibs: new Map([
        ['pokemonFile', ''],
        ['skillFile', ''],
        ['gameFile', '']
    ]),
    openNormalModal() {
      let modal = document.getElementById('normal')
      modal.showModal()
    },
    closeNormalModal() {
      let modal = document.getElementById('normal')
      modal.close();
    }
  })
})