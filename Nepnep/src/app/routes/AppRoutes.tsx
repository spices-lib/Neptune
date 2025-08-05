import { useRoutes } from 'react-router-dom'
import { routeConfig } from './RouteConfig'

export function AppRoutes() {
    return useRoutes(routeConfig)
}