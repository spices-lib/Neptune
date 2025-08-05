import { createRoot } from 'react-dom/client'
import { BrowserRouter } from 'react-router-dom'
import { App } from './app/App'

createRoot(document.getElementById('neptune')!).render(<BrowserRouter> <App /> </BrowserRouter>)