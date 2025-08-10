export const ROUTE_PATHS = {
    ROOT: '/',
    SIGN_IN: '/signin',
    SIGN_UP: '/signup',
    DASHBOARD: '/dashboard',
    USER_DASHBOARD: '/dashboard/:id'
} as const

export type RoutePath = typeof ROUTE_PATHS[keyof typeof ROUTE_PATHS]