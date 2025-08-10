import { RouteObject } from 'react-router-dom'
import SignInPage from '../signin/Page'
import SignUpPage from '../signup/Page'
import DashBoardPage from '../dashboard/Page'
import UserDashBoardPage from '../dashboard/[id]/Page'

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
    },
    {
        path: '/dashboard',
        element: <DashBoardPage />
    },
    {
        path: '/dashboard/:id',
        element: <UserDashBoardPage />
    }
]