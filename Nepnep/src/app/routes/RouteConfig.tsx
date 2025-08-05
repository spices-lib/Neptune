import { RouteObject } from 'react-router-dom'
import SignInPage from '../signin/Page'
import SignUpPage from '../signup/Page'

export const routeConfig: RouteObject[] = [
    {
        path: '/',
        element: <SignInPage />
    },
    {
        path: '/signin',
        element: <SignInPage />
    },
    {
        path: '/signup',
        element: <SignUpPage />
    }
]